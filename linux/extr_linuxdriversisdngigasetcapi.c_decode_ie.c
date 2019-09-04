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

/* Variables and functions */
 int /*<<< orphan*/  hex_asc_hi (int) ; 
 int /*<<< orphan*/  hex_asc_lo (int) ; 
 void* toupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_ie(u8 *in, char *out)
{
	int i = *in;
	while (i-- > 0) {
		/* ToDo: conversion to upper case necessary? */
		*out++ = toupper(hex_asc_hi(*++in));
		*out++ = toupper(hex_asc_lo(*in));
	}
}