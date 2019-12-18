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
 int /*<<< orphan*/  DOC_ECCCONF0 ; 
 int /*<<< orphan*/  DOC_ECCCONF0_READ_MODE ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_writew (struct docg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_ecc_disable(struct docg3 *docg3)
{
	doc_writew(docg3, DOC_ECCCONF0_READ_MODE, DOC_ECCCONF0);
	doc_delay(docg3, 4);
}