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
typedef  int u32 ;
struct watchdog_device {int timeout; } ;
struct npcm_wdt {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int NPCM_WTE ; 
 int NPCM_WTIE ; 
 int NPCM_WTR ; 
 int NPCM_WTRE ; 
 struct npcm_wdt* to_npcm_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm_wdt_start(struct watchdog_device *wdd)
{
	struct npcm_wdt *wdt = to_npcm_wdt(wdd);
	u32 val;

	if (wdd->timeout < 2)
		val = 0x800;
	else if (wdd->timeout < 3)
		val = 0x420;
	else if (wdd->timeout < 6)
		val = 0x810;
	else if (wdd->timeout < 11)
		val = 0x430;
	else if (wdd->timeout < 22)
		val = 0x820;
	else if (wdd->timeout < 44)
		val = 0xC00;
	else if (wdd->timeout < 87)
		val = 0x830;
	else if (wdd->timeout < 173)
		val = 0xC10;
	else if (wdd->timeout < 688)
		val = 0xC20;
	else
		val = 0xC30;

	val |= NPCM_WTRE | NPCM_WTE | NPCM_WTR | NPCM_WTIE;

	writel(val, wdt->reg);

	return 0;
}