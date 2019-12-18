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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int /*<<< orphan*/  auth_list; int /*<<< orphan*/  asoc_list; int /*<<< orphan*/  sta_recvpriv; int /*<<< orphan*/  sta_xmitpriv; int /*<<< orphan*/  hash_list; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _r8712_init_sta_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _r8712_init_sta_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _init_stainfo(struct sta_info *psta)
{
	memset((u8 *)psta, 0, sizeof(struct sta_info));
	spin_lock_init(&psta->lock);
	INIT_LIST_HEAD(&psta->list);
	INIT_LIST_HEAD(&psta->hash_list);
	_r8712_init_sta_xmit_priv(&psta->sta_xmitpriv);
	_r8712_init_sta_recv_priv(&psta->sta_recvpriv);
	INIT_LIST_HEAD(&psta->asoc_list);
	INIT_LIST_HEAD(&psta->auth_list);
}