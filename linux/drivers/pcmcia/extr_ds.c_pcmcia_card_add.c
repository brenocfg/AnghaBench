#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_socket {unsigned int functions; int /*<<< orphan*/  dev; int /*<<< orphan*/  ops_mutex; int /*<<< orphan*/  resource_setup_done; } ;
struct TYPE_3__ {unsigned int nfn; } ;
typedef  TYPE_1__ cistpl_longlink_mfc_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_FN_ALL ; 
 int /*<<< orphan*/  CISTPL_LONGLINK_MFC ; 
 int EAGAIN ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pccard_read_tuple (struct pcmcia_socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int pccard_validate_cis (struct pcmcia_socket*,unsigned int*) ; 
 int /*<<< orphan*/  pcmcia_device_add (struct pcmcia_socket*,unsigned int) ; 
 int /*<<< orphan*/  pcmcia_replace_cis (struct pcmcia_socket*,char*,int) ; 
 scalar_t__ pcmcia_validate_mem (struct pcmcia_socket*) ; 

__attribute__((used)) static int pcmcia_card_add(struct pcmcia_socket *s)
{
	cistpl_longlink_mfc_t mfc;
	unsigned int no_funcs, i, no_chains;
	int ret = -EAGAIN;

	mutex_lock(&s->ops_mutex);
	if (!(s->resource_setup_done)) {
		dev_dbg(&s->dev,
			   "no resources available, delaying card_add\n");
		mutex_unlock(&s->ops_mutex);
		return -EAGAIN; /* try again, but later... */
	}

	if (pcmcia_validate_mem(s)) {
		dev_dbg(&s->dev, "validating mem resources failed, "
		       "delaying card_add\n");
		mutex_unlock(&s->ops_mutex);
		return -EAGAIN; /* try again, but later... */
	}
	mutex_unlock(&s->ops_mutex);

	ret = pccard_validate_cis(s, &no_chains);
	if (ret || !no_chains) {
#if defined(CONFIG_MTD_PCMCIA_ANONYMOUS)
		/* Set up as an anonymous card. If we don't have anonymous
		   memory support then just error the card as there is no
		   point trying to second guess.

		   Note: some cards have just a device entry, it may be
		   worth extending support to cover these in future */
		if (ret == -EIO) {
			dev_info(&s->dev, "no CIS, assuming an anonymous memory card.\n");
			pcmcia_replace_cis(s, "\xFF", 1);
			no_chains = 1;
			ret = 0;
		} else
#endif
		{
			dev_dbg(&s->dev, "invalid CIS or invalid resources\n");
			return -ENODEV;
		}
	}

	if (!pccard_read_tuple(s, BIND_FN_ALL, CISTPL_LONGLINK_MFC, &mfc))
		no_funcs = mfc.nfn;
	else
		no_funcs = 1;
	s->functions = no_funcs;

	for (i = 0; i < no_funcs; i++)
		pcmcia_device_add(s, i);

	return ret;
}