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
struct TYPE_3__ {scalar_t__* TupleData; scalar_t__ TupleDataLen; } ;
typedef  TYPE_1__ tuple_t ;
struct ssb_sprom {int /*<<< orphan*/  il0mac; } ;
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CISTPL_FUNCE_LAN_NODE_ID ; 
 int EINVAL ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int ssb_pcmcia_get_mac(struct pcmcia_device *p_dev,
			tuple_t *tuple,
			void *priv)
{
	struct ssb_sprom *sprom = priv;

	if (tuple->TupleData[0] != CISTPL_FUNCE_LAN_NODE_ID)
		return -EINVAL;
	if (tuple->TupleDataLen != ETH_ALEN + 2)
		return -EINVAL;
	if (tuple->TupleData[1] != ETH_ALEN)
		return -EINVAL;
	memcpy(sprom->il0mac, &tuple->TupleData[2], ETH_ALEN);
	return 0;
}