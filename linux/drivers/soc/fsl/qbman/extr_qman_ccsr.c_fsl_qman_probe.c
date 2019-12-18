#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QMAN_CHANNEL_CAAM_REV3 ; 
 int /*<<< orphan*/  QMAN_CHANNEL_POOL1_REV3 ; 
 int QMAN_REV11 ; 
 int QMAN_REV12 ; 
 int QMAN_REV20 ; 
 int QMAN_REV30 ; 
 int QMAN_REV31 ; 
 int QMAN_REV32 ; 
 int /*<<< orphan*/  REG_ERR_IER ; 
 int /*<<< orphan*/  REG_ERR_ISR ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int __qman_probed ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  devm_gen_pool_create (struct device*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device*) ; 
 scalar_t__ fqd_a ; 
 int /*<<< orphan*/  fqd_sz ; 
 scalar_t__ pfdr_a ; 
 int /*<<< orphan*/  pfdr_sz ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qbman_init_private_mem (struct device*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_ccsr_out (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qm_ccsr_start ; 
 int /*<<< orphan*/  qm_cgralloc ; 
 int /*<<< orphan*/  qm_channel_caam ; 
 int /*<<< orphan*/  qm_channel_pool1 ; 
 int /*<<< orphan*/  qm_fqalloc ; 
 int /*<<< orphan*/  qm_get_fqid_maxcnt () ; 
 int /*<<< orphan*/  qm_get_version (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  qm_qpalloc ; 
 int qman_alloc_fq_table (int /*<<< orphan*/ ) ; 
 int qman_init_ccsr (struct device*) ; 
 int qman_ip_rev ; 
 int /*<<< orphan*/  qman_isr ; 
 int qman_resource_init (struct device*) ; 
 int qman_wq_alloc () ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  zero_priv_mem (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_qman_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct resource *res;
	int ret, err_irq;
	u16 id;
	u8 major, minor;

	__qman_probed = -1;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "Can't get %pOF property 'IORESOURCE_MEM'\n",
			node);
		return -ENXIO;
	}
	qm_ccsr_start = devm_ioremap(dev, res->start, resource_size(res));
	if (!qm_ccsr_start)
		return -ENXIO;

	qm_get_version(&id, &major, &minor);
	if (major == 1 && minor == 0) {
		dev_err(dev, "Rev1.0 on P4080 rev1 is not supported!\n");
			return -ENODEV;
	} else if (major == 1 && minor == 1)
		qman_ip_rev = QMAN_REV11;
	else if	(major == 1 && minor == 2)
		qman_ip_rev = QMAN_REV12;
	else if (major == 2 && minor == 0)
		qman_ip_rev = QMAN_REV20;
	else if (major == 3 && minor == 0)
		qman_ip_rev = QMAN_REV30;
	else if (major == 3 && minor == 1)
		qman_ip_rev = QMAN_REV31;
	else if (major == 3 && minor == 2)
		qman_ip_rev = QMAN_REV32;
	else {
		dev_err(dev, "Unknown QMan version\n");
		return -ENODEV;
	}

	if ((qman_ip_rev & 0xff00) >= QMAN_REV30) {
		qm_channel_pool1 = QMAN_CHANNEL_POOL1_REV3;
		qm_channel_caam = QMAN_CHANNEL_CAAM_REV3;
	}

	if (fqd_a) {
#ifdef CONFIG_PPC
		/*
		 * For PPC backward DT compatibility
		 * FQD memory MUST be zero'd by software
		 */
		zero_priv_mem(fqd_a, fqd_sz);
#else
		WARN(1, "Unexpected architecture using non shared-dma-mem reservations");
#endif
	} else {
		/*
		 * Order of memory regions is assumed as FQD followed by PFDR
		 * in order to ensure allocations from the correct regions the
		 * driver initializes then allocates each piece in order
		 */
		ret = qbman_init_private_mem(dev, 0, &fqd_a, &fqd_sz);
		if (ret) {
			dev_err(dev, "qbman_init_private_mem() for FQD failed 0x%x\n",
				ret);
			return -ENODEV;
		}
	}
	dev_dbg(dev, "Allocated FQD 0x%llx 0x%zx\n", fqd_a, fqd_sz);

	if (!pfdr_a) {
		/* Setup PFDR memory */
		ret = qbman_init_private_mem(dev, 1, &pfdr_a, &pfdr_sz);
		if (ret) {
			dev_err(dev, "qbman_init_private_mem() for PFDR failed 0x%x\n",
				ret);
			return -ENODEV;
		}
	}
	dev_dbg(dev, "Allocated PFDR 0x%llx 0x%zx\n", pfdr_a, pfdr_sz);

	ret = qman_init_ccsr(dev);
	if (ret) {
		dev_err(dev, "CCSR setup failed\n");
		return ret;
	}

	err_irq = platform_get_irq(pdev, 0);
	if (err_irq <= 0) {
		dev_info(dev, "Can't get %pOF property 'interrupts'\n",
			 node);
		return -ENODEV;
	}
	ret = devm_request_irq(dev, err_irq, qman_isr, IRQF_SHARED, "qman-err",
			       dev);
	if (ret)  {
		dev_err(dev, "devm_request_irq() failed %d for '%pOF'\n",
			ret, node);
		return ret;
	}

	/*
	 * Write-to-clear any stale bits, (eg. starvation being asserted prior
	 * to resource allocation during driver init).
	 */
	qm_ccsr_out(REG_ERR_ISR, 0xffffffff);
	/* Enable Error Interrupts */
	qm_ccsr_out(REG_ERR_IER, 0xffffffff);

	qm_fqalloc = devm_gen_pool_create(dev, 0, -1, "qman-fqalloc");
	if (IS_ERR(qm_fqalloc)) {
		ret = PTR_ERR(qm_fqalloc);
		dev_err(dev, "qman-fqalloc pool init failed (%d)\n", ret);
		return ret;
	}

	qm_qpalloc = devm_gen_pool_create(dev, 0, -1, "qman-qpalloc");
	if (IS_ERR(qm_qpalloc)) {
		ret = PTR_ERR(qm_qpalloc);
		dev_err(dev, "qman-qpalloc pool init failed (%d)\n", ret);
		return ret;
	}

	qm_cgralloc = devm_gen_pool_create(dev, 0, -1, "qman-cgralloc");
	if (IS_ERR(qm_cgralloc)) {
		ret = PTR_ERR(qm_cgralloc);
		dev_err(dev, "qman-cgralloc pool init failed (%d)\n", ret);
		return ret;
	}

	ret = qman_resource_init(dev);
	if (ret)
		return ret;

	ret = qman_alloc_fq_table(qm_get_fqid_maxcnt());
	if (ret)
		return ret;

	ret = qman_wq_alloc();
	if (ret)
		return ret;

	__qman_probed = 1;

	return 0;
}