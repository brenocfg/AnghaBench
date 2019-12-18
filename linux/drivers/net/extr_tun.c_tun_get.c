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
struct tun_struct {int /*<<< orphan*/  dev; } ;
struct tun_file {int /*<<< orphan*/  tun; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 struct tun_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct tun_struct *tun_get(struct tun_file *tfile)
{
	struct tun_struct *tun;

	rcu_read_lock();
	tun = rcu_dereference(tfile->tun);
	if (tun)
		dev_hold(tun->dev);
	rcu_read_unlock();

	return tun;
}