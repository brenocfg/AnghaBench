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
struct tty_struct {int dummy; } ;
struct pps_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  alias_n_tty_close (struct tty_struct*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct pps_device* pps_lookup_dev (struct tty_struct*) ; 
 int /*<<< orphan*/  pps_unregister_source (struct pps_device*) ; 

__attribute__((used)) static void pps_tty_close(struct tty_struct *tty)
{
	struct pps_device *pps = pps_lookup_dev(tty);

	alias_n_tty_close(tty);

	if (WARN_ON(!pps))
		return;

	dev_info(pps->dev, "removed\n");
	pps_unregister_source(pps);
}