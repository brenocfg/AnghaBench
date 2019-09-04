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
struct host1x_syncpt {int dummy; } ;
struct host1x {struct host1x_syncpt* syncpt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  host1x_hw_syncpt_load (struct host1x*,struct host1x_syncpt*) ; 
 int /*<<< orphan*/  host1x_hw_syncpt_load_wait_base (struct host1x*,struct host1x_syncpt*) ; 
 scalar_t__ host1x_syncpt_client_managed (struct host1x_syncpt*) ; 
 int /*<<< orphan*/  host1x_syncpt_idle (struct host1x_syncpt*) ; 
 unsigned int host1x_syncpt_nb_bases (struct host1x*) ; 
 unsigned int host1x_syncpt_nb_pts (struct host1x*) ; 

void host1x_syncpt_save(struct host1x *host)
{
	struct host1x_syncpt *sp_base = host->syncpt;
	unsigned int i;

	for (i = 0; i < host1x_syncpt_nb_pts(host); i++) {
		if (host1x_syncpt_client_managed(sp_base + i))
			host1x_hw_syncpt_load(host, sp_base + i);
		else
			WARN_ON(!host1x_syncpt_idle(sp_base + i));
	}

	for (i = 0; i < host1x_syncpt_nb_bases(host); i++)
		host1x_hw_syncpt_load_wait_base(host, sp_base + i);
}