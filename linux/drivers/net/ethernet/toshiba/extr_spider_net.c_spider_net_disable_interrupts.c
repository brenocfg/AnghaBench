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
struct spider_net_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPIDER_NET_GHIINT0MSK ; 
 int /*<<< orphan*/  SPIDER_NET_GHIINT1MSK ; 
 int /*<<< orphan*/  SPIDER_NET_GHIINT2MSK ; 
 int /*<<< orphan*/  SPIDER_NET_GMACINTEN ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_disable_interrupts(struct spider_net_card *card)
{
	spider_net_write_reg(card, SPIDER_NET_GHIINT0MSK, 0);
	spider_net_write_reg(card, SPIDER_NET_GHIINT1MSK, 0);
	spider_net_write_reg(card, SPIDER_NET_GHIINT2MSK, 0);
	spider_net_write_reg(card, SPIDER_NET_GMACINTEN, 0);
}