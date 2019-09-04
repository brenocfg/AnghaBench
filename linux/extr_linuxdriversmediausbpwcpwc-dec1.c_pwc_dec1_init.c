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
struct pwc_dec1_private {int /*<<< orphan*/  version; } ;
struct pwc_device {int /*<<< orphan*/  release; struct pwc_dec1_private dec1; } ;

/* Variables and functions */

void pwc_dec1_init(struct pwc_device *pdev, const unsigned char *cmd)
{
	struct pwc_dec1_private *pdec = &pdev->dec1;

	pdec->version = pdev->release;
}