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
typedef  int /*<<< orphan*/  u8 ;
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_ASICMODE ; 
 int /*<<< orphan*/  DOC_ASICMODECONFIRM ; 
 int /*<<< orphan*/  DOC_ASICMODE_MDWREN ; 
 int /*<<< orphan*/  DOC_IOSPACE_IPL ; 
 int /*<<< orphan*/  doc_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_set_asic_mode(struct docg3 *docg3, u8 mode)
{
	int i;

	for (i = 0; i < 12; i++)
		doc_readb(docg3, DOC_IOSPACE_IPL);

	mode |= DOC_ASICMODE_MDWREN;
	doc_dbg("doc_set_asic_mode(%02x)\n", mode);
	doc_writeb(docg3, mode, DOC_ASICMODE);
	doc_writeb(docg3, ~mode, DOC_ASICMODECONFIRM);
	doc_delay(docg3, 1);
}