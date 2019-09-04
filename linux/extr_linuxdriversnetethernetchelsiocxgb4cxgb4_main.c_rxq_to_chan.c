#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sge {TYPE_1__** ingr_map; scalar_t__ ingr_start; } ;
struct TYPE_4__ {unsigned int tx_chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 TYPE_2__* netdev2pinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rxq_to_chan(const struct sge *p, unsigned int qid)
{
	qid -= p->ingr_start;
	return netdev2pinfo(p->ingr_map[qid]->netdev)->tx_chan;
}