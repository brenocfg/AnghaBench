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
struct c8sectpfe {int num_feeds; int /*<<< orphan*/  adapter; int /*<<< orphan*/ * demux; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct c8sectpfe*) ; 
 int /*<<< orphan*/  unregister_dvb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void c8sectpfe_delete(struct c8sectpfe *c8sectpfe)
{
	int i;

	if (!c8sectpfe)
		return;

	for (i = 0; i < c8sectpfe->num_feeds; i++)
		unregister_dvb(&c8sectpfe->demux[i]);

	dvb_unregister_adapter(&c8sectpfe->adapter);

	kfree(c8sectpfe);
}