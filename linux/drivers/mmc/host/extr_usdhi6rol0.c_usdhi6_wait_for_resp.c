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
struct usdhi6_host {int dummy; } ;

/* Variables and functions */
 int USDHI6_SD_INFO1_ACCESS_END ; 
 int USDHI6_SD_INFO1_CARD_CD ; 
 int USDHI6_SD_INFO1_RSP_END ; 
 int /*<<< orphan*/  USDHI6_SD_INFO2_ERR ; 
 int /*<<< orphan*/  usdhi6_irq_enable (struct usdhi6_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_wait_for_resp(struct usdhi6_host *host)
{
	usdhi6_irq_enable(host, USDHI6_SD_INFO1_RSP_END |
			  USDHI6_SD_INFO1_ACCESS_END | USDHI6_SD_INFO1_CARD_CD,
			  USDHI6_SD_INFO2_ERR);
}