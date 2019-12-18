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
typedef  int /*<<< orphan*/  u32 ;
struct tb_switch {int dummy; } ;
struct nvm_auth_status {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 struct nvm_auth_status* __nvm_get_auth_status (struct tb_switch const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_auth_status_lock ; 

__attribute__((used)) static void nvm_get_auth_status(const struct tb_switch *sw, u32 *status)
{
	struct nvm_auth_status *st;

	mutex_lock(&nvm_auth_status_lock);
	st = __nvm_get_auth_status(sw);
	mutex_unlock(&nvm_auth_status_lock);

	*status = st ? st->status : 0;
}