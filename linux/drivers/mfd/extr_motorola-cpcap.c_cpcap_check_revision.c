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
typedef  scalar_t__ u16 ;
struct cpcap_ddata {TYPE_1__* spi; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CPCAP_REVISION_2_1 ; 
 int /*<<< orphan*/  CPCAP_REVISION_MAJOR (scalar_t__) ; 
 int /*<<< orphan*/  CPCAP_REVISION_MINOR (scalar_t__) ; 
 scalar_t__ CPCAP_VENDOR_ST ; 
 int ENODEV ; 
 int cpcap_get_revision (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int cpcap_get_vendor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int cpcap_check_revision(struct cpcap_ddata *cpcap)
{
	u16 vendor, rev;
	int ret;

	ret = cpcap_get_vendor(&cpcap->spi->dev, cpcap->regmap, &vendor);
	if (ret)
		return ret;

	ret = cpcap_get_revision(&cpcap->spi->dev, cpcap->regmap, &rev);
	if (ret)
		return ret;

	dev_info(&cpcap->spi->dev, "CPCAP vendor: %s rev: %i.%i (%x)\n",
		 vendor == CPCAP_VENDOR_ST ? "ST" : "TI",
		 CPCAP_REVISION_MAJOR(rev), CPCAP_REVISION_MINOR(rev),
		 rev);

	if (rev < CPCAP_REVISION_2_1) {
		dev_info(&cpcap->spi->dev,
			 "Please add old CPCAP revision support as needed\n");
		return -ENODEV;
	}

	return 0;
}