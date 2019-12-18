#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct enetc_si {TYPE_1__* pdev; } ;
struct enetc_cbd {int cmd; int cls; void** addr; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__* PTR_ALIGN (scalar_t__*,int) ; 
 int RSSE_ALIGN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int enetc_send_cmd (struct enetc_si*,struct enetc_cbd*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_cmd_rss_table(struct enetc_si *si, u32 *table, int count,
			       bool read)
{
	struct enetc_cbd cbd = {.cmd = 0};
	dma_addr_t dma, dma_align;
	u8 *tmp, *tmp_align;
	int err, i;

	if (count < RSSE_ALIGN)
		/* HW only takes in a full 64 entry table */
		return -EINVAL;

	tmp = dma_alloc_coherent(&si->pdev->dev, count + RSSE_ALIGN,
				 &dma, GFP_KERNEL);
	if (!tmp) {
		dev_err(&si->pdev->dev, "DMA mapping of RSS table failed!\n");
		return -ENOMEM;
	}
	dma_align = ALIGN(dma, RSSE_ALIGN);
	tmp_align = PTR_ALIGN(tmp, RSSE_ALIGN);

	if (!read)
		for (i = 0; i < count; i++)
			tmp_align[i] = (u8)(table[i]);

	/* fill up the descriptor */
	cbd.cmd = read ? 2 : 1;
	cbd.cls = 3;
	cbd.length = cpu_to_le16(count);

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma_align));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma_align));

	err = enetc_send_cmd(si, &cbd);
	if (err)
		dev_err(&si->pdev->dev, "RSS cmd failed (%d)!", err);

	if (read)
		for (i = 0; i < count; i++)
			table[i] = tmp_align[i];

	dma_free_coherent(&si->pdev->dev, count + RSSE_ALIGN, tmp, dma);

	return err;
}