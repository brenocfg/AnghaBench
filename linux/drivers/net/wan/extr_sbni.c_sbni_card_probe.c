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

/* Variables and functions */
 unsigned char BU_EMP ; 
 scalar_t__ CSR0 ; 
 int ENODEV ; 
 unsigned char EN_INT ; 
 int VALID_DECODER ; 
 unsigned char inb (scalar_t__) ; 

__attribute__((used)) static int
sbni_card_probe( unsigned long  ioaddr )
{
	unsigned char  csr0;

	csr0 = inb( ioaddr + CSR0 );
	if( csr0 != 0xff  &&  csr0 != 0x00 ) {
		csr0 &= ~EN_INT;
		if( csr0 & BU_EMP )
			csr0 |= EN_INT;
      
		if( VALID_DECODER & (1 << (csr0 >> 4)) )
			return  0;
	}
   
	return  -ENODEV;
}