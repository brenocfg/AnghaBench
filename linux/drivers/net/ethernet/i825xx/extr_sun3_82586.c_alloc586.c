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
struct scp_struct {int /*<<< orphan*/  sysbus; void* iscp; } ;
struct scb_struct {int dummy; } ;
struct priv {struct scb_struct* scb; scalar_t__ reseted; struct iscp_struct* iscp; struct scp_struct* scp; scalar_t__ base; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  mem_start; } ;
struct iscp_struct {int busy; void* scb_base; int /*<<< orphan*/  scb_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ SCP_DEFAULT_ADDRESS ; 
 int /*<<< orphan*/  SYSBUSVAL ; 
 struct iscp_struct* dvma_btov (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make16 (struct scb_struct*) ; 
 void* make24 (struct iscp_struct*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun3_attn586 () ; 
 int /*<<< orphan*/  sun3_reset586 () ; 

__attribute__((used)) static void alloc586(struct net_device *dev)
{
	struct priv *p = netdev_priv(dev);

	sun3_reset586();
	DELAY(1);

	p->scp	= (struct scp_struct *)	(p->base + SCP_DEFAULT_ADDRESS);
	p->iscp	= (struct iscp_struct *) dvma_btov(dev->mem_start);
	p->scb  = (struct scb_struct *)  ((char *)p->iscp + sizeof(struct iscp_struct));

	memset((char *) p->iscp,0,sizeof(struct iscp_struct));
	memset((char *) p->scp ,0,sizeof(struct scp_struct));

	p->scp->iscp = make24(p->iscp);
	p->scp->sysbus = SYSBUSVAL;
	p->iscp->scb_offset = make16(p->scb);
	p->iscp->scb_base = make24(dvma_btov(dev->mem_start));

	p->iscp->busy = 1;
	sun3_reset586();
	sun3_attn586();

	DELAY(1);

	if(p->iscp->busy)
		printk("%s: Init-Problems (alloc).\n",dev->name);

	p->reseted = 0;

	memset((char *)p->scb,0,sizeof(struct scb_struct));
}