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
 unsigned short PCI_LOAD_INTERVAL ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned short) ; 

__attribute__((used)) static void mgsl_load_pci_memory( char* TargetPtr, const char* SourcePtr,
	unsigned short count )
{
	/* 16 32-bit writes @ 60ns each = 960ns max latency on local bus */
#define PCI_LOAD_INTERVAL 64

	unsigned short Intervalcount = count / PCI_LOAD_INTERVAL;
	unsigned short Index;
	unsigned long Dummy;

	for ( Index = 0 ; Index < Intervalcount ; Index++ )
	{
		memcpy(TargetPtr, SourcePtr, PCI_LOAD_INTERVAL);
		Dummy = *((volatile unsigned long *)TargetPtr);
		TargetPtr += PCI_LOAD_INTERVAL;
		SourcePtr += PCI_LOAD_INTERVAL;
	}

	memcpy( TargetPtr, SourcePtr, count % PCI_LOAD_INTERVAL );

}