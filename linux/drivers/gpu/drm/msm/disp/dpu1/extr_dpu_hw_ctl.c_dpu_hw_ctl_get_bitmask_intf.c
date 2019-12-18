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
struct dpu_hw_ctl {int dummy; } ;
typedef  enum dpu_intf { ____Placeholder_dpu_intf } dpu_intf ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
#define  INTF_0 131 
#define  INTF_1 130 
#define  INTF_2 129 
#define  INTF_3 128 

__attribute__((used)) static int dpu_hw_ctl_get_bitmask_intf(struct dpu_hw_ctl *ctx,
		u32 *flushbits, enum dpu_intf intf)
{
	switch (intf) {
	case INTF_0:
		*flushbits |= BIT(31);
		break;
	case INTF_1:
		*flushbits |= BIT(30);
		break;
	case INTF_2:
		*flushbits |= BIT(29);
		break;
	case INTF_3:
		*flushbits |= BIT(28);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}