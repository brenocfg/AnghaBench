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
struct mtdswap_dev {int /*<<< orphan*/  page_buf; int /*<<< orphan*/  oob_buf; int /*<<< orphan*/  page_data; int /*<<< orphan*/  revmap; int /*<<< orphan*/  eb_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtdswap_cleanup(struct mtdswap_dev *d)
{
	vfree(d->eb_data);
	vfree(d->revmap);
	vfree(d->page_data);
	kfree(d->oob_buf);
	kfree(d->page_buf);
}