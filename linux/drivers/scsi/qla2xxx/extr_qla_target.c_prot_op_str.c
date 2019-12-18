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
typedef  int u32 ;

/* Variables and functions */
#define  TARGET_PROT_DIN_INSERT 134 
#define  TARGET_PROT_DIN_PASS 133 
#define  TARGET_PROT_DIN_STRIP 132 
#define  TARGET_PROT_DOUT_INSERT 131 
#define  TARGET_PROT_DOUT_PASS 130 
#define  TARGET_PROT_DOUT_STRIP 129 
#define  TARGET_PROT_NORMAL 128 

__attribute__((used)) static const char *prot_op_str(u32 prot_op)
{
	switch (prot_op) {
	case TARGET_PROT_NORMAL:	return "NORMAL";
	case TARGET_PROT_DIN_INSERT:	return "DIN_INSERT";
	case TARGET_PROT_DOUT_INSERT:	return "DOUT_INSERT";
	case TARGET_PROT_DIN_STRIP:	return "DIN_STRIP";
	case TARGET_PROT_DOUT_STRIP:	return "DOUT_STRIP";
	case TARGET_PROT_DIN_PASS:	return "DIN_PASS";
	case TARGET_PROT_DOUT_PASS:	return "DOUT_PASS";
	default:			return "UNKNOWN";
	}
}