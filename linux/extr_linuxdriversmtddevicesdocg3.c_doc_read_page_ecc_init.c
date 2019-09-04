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
 int DOC_ECCCONF0_BCH_ENABLE ; 
 int DOC_ECCCONF0_DATA_BYTES_MASK ; 
 int DOC_ECCCONF0_HAMMING_ENABLE ; 
 int DOC_ECCCONF0_READ_MODE ; 
 int /*<<< orphan*/  DOC_FLASHCONTROL ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_wait_ready (struct docg3*) ; 
 int /*<<< orphan*/  doc_writew (struct docg3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doc_read_page_ecc_init(struct docg3 *docg3, int len)
{
	doc_writew(docg3, DOC_ECCCONF0_READ_MODE
		   | DOC_ECCCONF0_BCH_ENABLE | DOC_ECCCONF0_HAMMING_ENABLE
		   | (len & DOC_ECCCONF0_DATA_BYTES_MASK),
		   DOC_ECCCONF0);
	doc_delay(docg3, 4);
	doc_register_readb(docg3, DOC_FLASHCONTROL);
	return doc_wait_ready(docg3);
}