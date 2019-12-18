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
struct pattern_trig_data {size_t npatterns; TYPE_1__* patterns; } ;
struct TYPE_2__ {int /*<<< orphan*/  delta_t; int /*<<< orphan*/  brightness; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAX_PATTERNS ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int pattern_trig_store_patterns_string(struct pattern_trig_data *data,
					      const char *buf, size_t count)
{
	int ccount, cr, offset = 0;

	while (offset < count - 1 && data->npatterns < MAX_PATTERNS) {
		cr = 0;
		ccount = sscanf(buf + offset, "%d %u %n",
				&data->patterns[data->npatterns].brightness,
				&data->patterns[data->npatterns].delta_t, &cr);
		if (ccount != 2) {
			data->npatterns = 0;
			return -EINVAL;
		}

		offset += cr;
		data->npatterns++;
	}

	return 0;
}