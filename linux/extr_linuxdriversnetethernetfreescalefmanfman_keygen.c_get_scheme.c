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
typedef  size_t u8 ;
struct keygen_scheme {int dummy; } ;
struct fman_keygen {struct keygen_scheme* schemes; } ;

/* Variables and functions */
 size_t FM_KG_MAX_NUM_OF_SCHEMES ; 

__attribute__((used)) static struct keygen_scheme *get_scheme(struct fman_keygen *keygen,
					u8 scheme_id)
{
	if (scheme_id >= FM_KG_MAX_NUM_OF_SCHEMES)
		return NULL;
	return &keygen->schemes[scheme_id];
}