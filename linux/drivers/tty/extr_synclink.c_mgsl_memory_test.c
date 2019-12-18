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
struct mgsl_struct {scalar_t__ bus_type; scalar_t__ memory_base; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (unsigned long*) ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int SHARED_MEM_ADDRESS_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool mgsl_memory_test( struct mgsl_struct *info )
{
	static unsigned long BitPatterns[] =
		{ 0x0, 0x55555555, 0xaaaaaaaa, 0x66666666, 0x99999999, 0xffffffff, 0x12345678 };
	unsigned long Patterncount = ARRAY_SIZE(BitPatterns);
	unsigned long i;
	unsigned long TestLimit = SHARED_MEM_ADDRESS_SIZE/sizeof(unsigned long);
	unsigned long * TestAddr;

	if ( info->bus_type != MGSL_BUS_TYPE_PCI )
		return true;

	TestAddr = (unsigned long *)info->memory_base;

	/* Test data lines with test pattern at one location. */

	for ( i = 0 ; i < Patterncount ; i++ ) {
		*TestAddr = BitPatterns[i];
		if ( *TestAddr != BitPatterns[i] )
			return false;
	}

	/* Test address lines with incrementing pattern over */
	/* entire address range. */

	for ( i = 0 ; i < TestLimit ; i++ ) {
		*TestAddr = i * 4;
		TestAddr++;
	}

	TestAddr = (unsigned long *)info->memory_base;

	for ( i = 0 ; i < TestLimit ; i++ ) {
		if ( *TestAddr != i * 4 )
			return false;
		TestAddr++;
	}

	memset( info->memory_base, 0, SHARED_MEM_ADDRESS_SIZE );

	return true;

}