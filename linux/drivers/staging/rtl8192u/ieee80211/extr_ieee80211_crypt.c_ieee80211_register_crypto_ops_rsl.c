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
struct ieee80211_crypto_ops {int /*<<< orphan*/  name; } ;
struct ieee80211_crypto_alg {int /*<<< orphan*/  list; struct ieee80211_crypto_ops* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  algs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* hcrypt ; 
 struct ieee80211_crypto_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ieee80211_register_crypto_ops(struct ieee80211_crypto_ops *ops)
{
	unsigned long flags;
	struct ieee80211_crypto_alg *alg;

	if (!hcrypt)
		return -1;

	alg = kzalloc(sizeof(*alg), GFP_KERNEL);
	if (!alg)
		return -ENOMEM;

	alg->ops = ops;

	spin_lock_irqsave(&hcrypt->lock, flags);
	list_add(&alg->list, &hcrypt->algs);
	spin_unlock_irqrestore(&hcrypt->lock, flags);

	pr_debug("ieee80211_crypt: registered algorithm '%s'\n",
	       ops->name);

	return 0;
}