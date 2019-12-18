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
struct nfc_dev {int dummy; } ;

/* Variables and functions */
 int pn533_rf_field (struct nfc_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pn533_dev_down(struct nfc_dev *nfc_dev)
{
	return pn533_rf_field(nfc_dev, 0);
}