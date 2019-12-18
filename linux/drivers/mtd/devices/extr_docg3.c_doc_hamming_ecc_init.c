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
typedef  int u8 ;
struct docg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_ECCCONF1 ; 
 int DOC_ECCCONF1_HAMMING_BITS_MASK ; 
 int doc_register_readb (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doc_hamming_ecc_init(struct docg3 *docg3, int nb_bytes)
{
	u8 ecc_conf1;

	ecc_conf1 = doc_register_readb(docg3, DOC_ECCCONF1);
	ecc_conf1 &= ~DOC_ECCCONF1_HAMMING_BITS_MASK;
	ecc_conf1 |= (nb_bytes & DOC_ECCCONF1_HAMMING_BITS_MASK);
	doc_writeb(docg3, ecc_conf1, DOC_ECCCONF1);
}