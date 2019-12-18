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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_NOP ; 
 int /*<<< orphan*/  doc_vdbg (char*,int) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_delay(struct docg3 *docg3, int nbNOPs)
{
	int i;

	doc_vdbg("NOP x %d\n", nbNOPs);
	for (i = 0; i < nbNOPs; i++)
		doc_writeb(docg3, 0, DOC_NOP);
}