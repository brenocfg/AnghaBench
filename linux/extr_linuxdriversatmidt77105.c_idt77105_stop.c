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
struct idt77105_priv {struct idt77105_priv* next; struct atm_dev* dev; } ;
struct atm_dev {int /*<<< orphan*/ * dev_data; int /*<<< orphan*/ * phy; int /*<<< orphan*/  number; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GET (int /*<<< orphan*/ ) ; 
 int IDT77105_MCR_EIP ; 
 int /*<<< orphan*/  MCR ; 
 int /*<<< orphan*/  PUT (int,int /*<<< orphan*/ ) ; 
 struct idt77105_priv* idt77105_all ; 
 int /*<<< orphan*/  kfree (struct idt77105_priv*) ; 

__attribute__((used)) static int idt77105_stop(struct atm_dev *dev)
{
	struct idt77105_priv *walk, *prev;

        DPRINTK("%s(itf %d): stopping IDT77105\n",dev->type,dev->number);
        
        /* disable interrupts */
	PUT( GET(MCR) & ~IDT77105_MCR_EIP, MCR );
        
        /* detach private struct from atm_dev & free */
	for (prev = NULL, walk = idt77105_all ;
             walk != NULL;
             prev = walk, walk = walk->next) {
            if (walk->dev == dev) {
                if (prev != NULL)
                    prev->next = walk->next;
                else
                    idt77105_all = walk->next;
	        dev->phy = NULL;
                dev->dev_data = NULL;
                kfree(walk);
                break;
            }
        }

	return 0;
}