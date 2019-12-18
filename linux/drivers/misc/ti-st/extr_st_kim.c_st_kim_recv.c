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
struct st_data_s {struct kim_data_s* kim_data; } ;
struct kim_data_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kim_int_recv (struct kim_data_s*,unsigned char const*,long) ; 

void st_kim_recv(void *disc_data, const unsigned char *data, long count)
{
	struct st_data_s	*st_gdata = (struct st_data_s *)disc_data;
	struct kim_data_s	*kim_gdata = st_gdata->kim_data;

	/* proceed to gather all data and distinguish read fw version response
	 * from other fw responses when data gathering is complete
	 */
	kim_int_recv(kim_gdata, data, count);
	return;
}