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
struct fru_type_length {int dummy; } ;
struct fru_common_header {int dummy; } ;

/* Variables and functions */
 struct fru_type_length* __fru_get_board_tl (struct fru_common_header*,int) ; 
 char* fru_alloc (scalar_t__) ; 
 char* fru_strcpy (char*,struct fru_type_length*) ; 
 scalar_t__ fru_strlen (struct fru_type_length*) ; 

__attribute__((used)) static char *__fru_alloc_get_tl(struct fru_common_header *header, int nr)
{
	struct fru_type_length *tl;
	char *res;

	tl = __fru_get_board_tl(header, nr);
	if (!tl)
		return NULL;

	res = fru_alloc(fru_strlen(tl) + 1);
	if (!res)
		return NULL;
	return fru_strcpy(res, tl);
}