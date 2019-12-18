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
struct qlogicfas408_priv {int qbase; int int_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG1 ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void qlogicfas408_disable_ints(struct qlogicfas408_priv *priv)
{
	int qbase = priv->qbase;
	int int_type = priv->int_type;

	REG1;
	outb(0, qbase + 0xb);	/* disable ints */
}