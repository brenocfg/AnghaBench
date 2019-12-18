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
struct TYPE_3__ {int TupleDataLen; int* TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct pcmcia_device {int dummy; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int pcmcia_get_mac_ce(struct pcmcia_device *p_dev,
			     tuple_t *tuple,
			     void *priv)
{
	struct net_device *dev = priv;
	int i;

	if (tuple->TupleDataLen != 13)
		return -EINVAL;
	if ((tuple->TupleData[0] != 2) || (tuple->TupleData[1] != 1) ||
		(tuple->TupleData[2] != 6))
		return -EINVAL;
	/* another try	(James Lehmer's CE2 version 4.1)*/
	for (i = 2; i < 6; i++)
		dev->dev_addr[i] = tuple->TupleData[i+2];
	return 0;
}