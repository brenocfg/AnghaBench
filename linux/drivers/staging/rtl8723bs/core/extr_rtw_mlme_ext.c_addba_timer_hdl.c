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
struct timer_list {int dummy; } ;
struct ht_priv {int candidate_tid_bitmap; scalar_t__ ampdu_enable; scalar_t__ ht_option; } ;
struct sta_info {struct ht_priv htpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  addba_retry_timer ; 
 struct sta_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sta_info* psta ; 

void addba_timer_hdl(struct timer_list *t)
{
	struct sta_info *psta = from_timer(psta, t, addba_retry_timer);
	struct ht_priv *phtpriv;

	if (!psta)
		return;

	phtpriv = &psta->htpriv;

	if (phtpriv->ht_option && phtpriv->ampdu_enable) {
		if (phtpriv->candidate_tid_bitmap)
			phtpriv->candidate_tid_bitmap = 0x0;

	}
}