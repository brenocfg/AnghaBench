#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_card {TYPE_1__* card; int /*<<< orphan*/  load; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_request_count; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool zcrypt_card_compare(struct zcrypt_card *zc,
				       struct zcrypt_card *pref_zc,
				       unsigned int weight,
				       unsigned int pref_weight)
{
	if (!pref_zc)
		return false;
	weight += atomic_read(&zc->load);
	pref_weight += atomic_read(&pref_zc->load);
	if (weight == pref_weight)
		return atomic_read(&zc->card->total_request_count) >
			atomic_read(&pref_zc->card->total_request_count);
	return weight > pref_weight;
}