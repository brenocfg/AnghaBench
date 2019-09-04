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
struct asymmetric_key_ids {struct asymmetric_key_id const** id; } ;
struct asymmetric_key_id {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct asymmetric_key_id const**) ; 

__attribute__((used)) static bool asymmetric_match_key_ids(
	const struct asymmetric_key_ids *kids,
	const struct asymmetric_key_id *match_id,
	bool (*match)(const struct asymmetric_key_id *kid1,
		      const struct asymmetric_key_id *kid2))
{
	int i;

	if (!kids || !match_id)
		return false;
	for (i = 0; i < ARRAY_SIZE(kids->id); i++)
		if (match(kids->id[i], match_id))
			return true;
	return false;
}