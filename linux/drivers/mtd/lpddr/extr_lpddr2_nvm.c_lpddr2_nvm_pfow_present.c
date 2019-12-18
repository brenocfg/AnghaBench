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
struct map_info {int dummy; } ;
typedef  int /*<<< orphan*/  map_word ;

/* Variables and functions */
 int /*<<< orphan*/  PFOW_QUERY_STRING_F ; 
 int /*<<< orphan*/  PFOW_QUERY_STRING_O ; 
 int /*<<< orphan*/  PFOW_QUERY_STRING_P ; 
 int /*<<< orphan*/  PFOW_QUERY_STRING_W ; 
 int /*<<< orphan*/  build_map_word (char) ; 
 int /*<<< orphan*/  lpdd2_nvm_mutex ; 
 int /*<<< orphan*/  map_read (struct map_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_word_equal (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ow_disable (struct map_info*) ; 
 int /*<<< orphan*/  ow_enable (struct map_info*) ; 
 int /*<<< orphan*/  ow_reg_add (struct map_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpddr2_nvm_pfow_present(struct map_info *map)
{
	map_word pfow_val[4];
	unsigned int found = 1;

	mutex_lock(&lpdd2_nvm_mutex);

	ow_enable(map);

	/* Load string from array */
	pfow_val[0] = map_read(map, ow_reg_add(map, PFOW_QUERY_STRING_P));
	pfow_val[1] = map_read(map, ow_reg_add(map, PFOW_QUERY_STRING_F));
	pfow_val[2] = map_read(map, ow_reg_add(map, PFOW_QUERY_STRING_O));
	pfow_val[3] = map_read(map, ow_reg_add(map, PFOW_QUERY_STRING_W));

	/* Verify the string loaded vs expected */
	if (!map_word_equal(map, build_map_word('P'), pfow_val[0]))
		found = 0;
	if (!map_word_equal(map, build_map_word('F'), pfow_val[1]))
		found = 0;
	if (!map_word_equal(map, build_map_word('O'), pfow_val[2]))
		found = 0;
	if (!map_word_equal(map, build_map_word('W'), pfow_val[3]))
		found = 0;

	ow_disable(map);

	mutex_unlock(&lpdd2_nvm_mutex);

	return found;
}