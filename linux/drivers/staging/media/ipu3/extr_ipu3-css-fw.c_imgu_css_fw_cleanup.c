#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imgu_device {int dummy; } ;
struct imgu_css {int /*<<< orphan*/ * fw; int /*<<< orphan*/ * binary; TYPE_2__* fwp; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int binary_nr; } ;
struct TYPE_4__ {TYPE_1__ file_header; } ;

/* Variables and functions */
 struct imgu_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_dmamap_free (struct imgu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

void imgu_css_fw_cleanup(struct imgu_css *css)
{
	struct imgu_device *imgu = dev_get_drvdata(css->dev);

	if (css->binary) {
		unsigned int i;

		for (i = 0; i < css->fwp->file_header.binary_nr; i++)
			imgu_dmamap_free(imgu, &css->binary[i]);
		kfree(css->binary);
	}
	if (css->fw)
		release_firmware(css->fw);

	css->binary = NULL;
	css->fw = NULL;
}