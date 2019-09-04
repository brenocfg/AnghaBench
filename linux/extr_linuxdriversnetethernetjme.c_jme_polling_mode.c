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
struct jme_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCC_OFF ; 
 int /*<<< orphan*/  jme_set_rx_pcc (struct jme_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
jme_polling_mode(struct jme_adapter *jme)
{
	jme_set_rx_pcc(jme, PCC_OFF);
}