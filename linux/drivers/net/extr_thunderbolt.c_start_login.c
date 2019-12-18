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
struct tbnet {int login_sent; int login_received; int /*<<< orphan*/  login_work; int /*<<< orphan*/  connection_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_long_wq ; 

__attribute__((used)) static void start_login(struct tbnet *net)
{
	mutex_lock(&net->connection_lock);
	net->login_sent = false;
	net->login_received = false;
	mutex_unlock(&net->connection_lock);

	queue_delayed_work(system_long_wq, &net->login_work,
			   msecs_to_jiffies(1000));
}