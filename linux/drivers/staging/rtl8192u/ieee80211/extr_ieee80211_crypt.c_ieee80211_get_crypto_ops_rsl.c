#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {struct list_head* next; } ;
struct ieee80211_crypto_ops {int /*<<< orphan*/  name; } ;
struct ieee80211_crypto_alg {struct ieee80211_crypto_ops* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct list_head algs; } ;

/* Variables and functions */
 TYPE_1__* hcrypt ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct ieee80211_crypto_ops *ieee80211_get_crypto_ops(const char *name)
{
	unsigned long flags;
	struct list_head *ptr;
	struct ieee80211_crypto_alg *found_alg = NULL;

	if (!hcrypt)
		return NULL;

	spin_lock_irqsave(&hcrypt->lock, flags);
	for (ptr = hcrypt->algs.next; ptr != &hcrypt->algs; ptr = ptr->next) {
		struct ieee80211_crypto_alg *alg =
			(struct ieee80211_crypto_alg *)ptr;
		if (strcmp(alg->ops->name, name) == 0) {
			found_alg = alg;
			break;
		}
	}
	spin_unlock_irqrestore(&hcrypt->lock, flags);

	if (found_alg)
		return found_alg->ops;
	return NULL;
}