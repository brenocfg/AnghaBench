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
struct nfcsim {int /*<<< orphan*/  link_in; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 struct nfcsim* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  nfcsim_link_recv_cancel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfcsim_abort_cmd(struct nfc_digital_dev *ddev)
{
	struct nfcsim *dev = nfc_digital_get_drvdata(ddev);

	nfcsim_link_recv_cancel(dev->link_in);
}