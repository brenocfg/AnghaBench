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
struct r5conf {scalar_t__ pending_data_cnt; int /*<<< orphan*/  pending_bios_lock; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 struct bio_list BIO_EMPTY_LIST ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dispatch_bio_list (struct bio_list*) ; 
 int /*<<< orphan*/  dispatch_defer_bios (struct r5conf*,scalar_t__,struct bio_list*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_deferred_bios(struct r5conf *conf)
{
	struct bio_list tmp = BIO_EMPTY_LIST;

	if (conf->pending_data_cnt == 0)
		return;

	spin_lock(&conf->pending_bios_lock);
	dispatch_defer_bios(conf, conf->pending_data_cnt, &tmp);
	BUG_ON(conf->pending_data_cnt != 0);
	spin_unlock(&conf->pending_bios_lock);

	dispatch_bio_list(&tmp);
}