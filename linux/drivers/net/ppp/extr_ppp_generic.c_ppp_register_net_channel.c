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
struct ppp_net {int /*<<< orphan*/  all_channels_lock; int /*<<< orphan*/  new_channels; scalar_t__ last_channel_index; } ;
struct ppp_channel {int /*<<< orphan*/  hdrlen; struct channel* ppp; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ index; int /*<<< orphan*/  hdrlen; } ;
struct channel {int lastseq; int /*<<< orphan*/  list; TYPE_1__ file; int /*<<< orphan*/  upl; int /*<<< orphan*/  downl; int /*<<< orphan*/  chan_sem; int /*<<< orphan*/  chan_net; struct ppp_channel* chan; int /*<<< orphan*/ * ppp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_count ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  init_ppp_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ppp_net* ppp_pernet (struct net*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ppp_register_net_channel(struct net *net, struct ppp_channel *chan)
{
	struct channel *pch;
	struct ppp_net *pn;

	pch = kzalloc(sizeof(struct channel), GFP_KERNEL);
	if (!pch)
		return -ENOMEM;

	pn = ppp_pernet(net);

	pch->ppp = NULL;
	pch->chan = chan;
	pch->chan_net = get_net(net);
	chan->ppp = pch;
	init_ppp_file(&pch->file, CHANNEL);
	pch->file.hdrlen = chan->hdrlen;
#ifdef CONFIG_PPP_MULTILINK
	pch->lastseq = -1;
#endif /* CONFIG_PPP_MULTILINK */
	init_rwsem(&pch->chan_sem);
	spin_lock_init(&pch->downl);
	rwlock_init(&pch->upl);

	spin_lock_bh(&pn->all_channels_lock);
	pch->file.index = ++pn->last_channel_index;
	list_add(&pch->list, &pn->new_channels);
	atomic_inc(&channel_count);
	spin_unlock_bh(&pn->all_channels_lock);

	return 0;
}