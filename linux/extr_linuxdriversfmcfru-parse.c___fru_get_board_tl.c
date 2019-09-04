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
struct fru_board_info_area {struct fru_type_length* tl; } ;

/* Variables and functions */
 struct fru_board_info_area* fru_get_board_area (struct fru_common_header*) ; 
 scalar_t__ fru_is_eof (struct fru_type_length*) ; 
 struct fru_type_length* fru_next_tl (struct fru_type_length*) ; 

__attribute__((used)) static struct fru_type_length *
__fru_get_board_tl(struct fru_common_header *header, int nr)
{
	struct fru_board_info_area *bia;
	struct fru_type_length *tl;

	bia = fru_get_board_area(header);
	tl = bia->tl;
	while (nr > 0 && !fru_is_eof(tl)) {
		tl = fru_next_tl(tl);
		nr--;
	}
	if (fru_is_eof(tl))
		return NULL;
	return tl;
}