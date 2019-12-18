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
struct fc_disc {int /*<<< orphan*/  rports; int /*<<< orphan*/  disc_mutex; int /*<<< orphan*/  disc_work; } ;
struct fc_lport {struct fc_disc disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_disc_timeout ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void fc_disc_init(struct fc_lport *lport)
{
	struct fc_disc *disc = &lport->disc;

	INIT_DELAYED_WORK(&disc->disc_work, fc_disc_timeout);
	mutex_init(&disc->disc_mutex);
	INIT_LIST_HEAD(&disc->rports);
}