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
typedef  enum spu2_cipher_type { ____Placeholder_spu2_cipher_type } spu2_cipher_type ;

/* Variables and functions */
 int SPU2_CIPHER_TYPE_LAST ; 
 char** spu2_cipher_type_names ; 

__attribute__((used)) static char *spu2_ciph_type_name(enum spu2_cipher_type cipher_type)
{
	if (cipher_type >= SPU2_CIPHER_TYPE_LAST)
		return "Reserved";
	return spu2_cipher_type_names[cipher_type];
}