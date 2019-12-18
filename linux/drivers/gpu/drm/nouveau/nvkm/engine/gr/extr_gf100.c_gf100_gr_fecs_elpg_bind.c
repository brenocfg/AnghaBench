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
typedef  int /*<<< orphan*/  u32 ;
struct gf100_gr {int dummy; } ;

/* Variables and functions */
 int gf100_gr_fecs_discover_reglist_image_size (struct gf100_gr*,int /*<<< orphan*/ *) ; 
 int gf100_gr_fecs_set_reglist_bind_instance (struct gf100_gr*,int /*<<< orphan*/ ) ; 
 int gf100_gr_fecs_set_reglist_virtual_address (struct gf100_gr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gf100_gr_fecs_elpg_bind(struct gf100_gr *gr)
{
	u32 size;
	int ret;

	ret = gf100_gr_fecs_discover_reglist_image_size(gr, &size);
	if (ret)
		return ret;

	/*XXX: We need to allocate + map the above into PMU's inst block,
	 *     which which means we probably need a proper PMU before we
	 *     even bother.
	 */

	ret = gf100_gr_fecs_set_reglist_bind_instance(gr, 0);
	if (ret)
		return ret;

	return gf100_gr_fecs_set_reglist_virtual_address(gr, 0);
}