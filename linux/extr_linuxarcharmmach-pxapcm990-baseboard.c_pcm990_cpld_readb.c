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

/* Variables and functions */
 scalar_t__ pcm990_cpld_base ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static u8 pcm990_cpld_readb(unsigned int reg)
{
	return readb(pcm990_cpld_base + reg);
}