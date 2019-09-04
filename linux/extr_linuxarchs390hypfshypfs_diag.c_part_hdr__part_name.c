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
struct diag204_x_part_hdr {int /*<<< orphan*/  part_name; } ;
struct diag204_part_hdr {int /*<<< orphan*/  part_name; } ;
typedef  enum diag204_format { ____Placeholder_diag204_format } diag204_format ;

/* Variables and functions */
 int DIAG204_INFO_SIMPLE ; 
 size_t DIAG204_LPAR_NAME_LEN ; 
 int /*<<< orphan*/  EBCASC (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static inline void part_hdr__part_name(enum diag204_format type, void *hdr,
				       char *name)
{
	if (type == DIAG204_INFO_SIMPLE)
		memcpy(name, ((struct diag204_part_hdr *)hdr)->part_name,
		       DIAG204_LPAR_NAME_LEN);
	else /* DIAG204_INFO_EXT */
		memcpy(name, ((struct diag204_x_part_hdr *)hdr)->part_name,
		       DIAG204_LPAR_NAME_LEN);
	EBCASC(name, DIAG204_LPAR_NAME_LEN);
	name[DIAG204_LPAR_NAME_LEN] = 0;
	strim(name);
}