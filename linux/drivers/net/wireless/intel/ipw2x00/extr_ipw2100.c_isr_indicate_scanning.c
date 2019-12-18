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
typedef  int /*<<< orphan*/  u32 ;
struct ipw2100_priv {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_SCAN (char*) ; 
 int /*<<< orphan*/  STATUS_SCANNING ; 

__attribute__((used)) static void isr_indicate_scanning(struct ipw2100_priv *priv, u32 status)
{
	IPW_DEBUG_SCAN("Scanning...\n");
	priv->status |= STATUS_SCANNING;
}