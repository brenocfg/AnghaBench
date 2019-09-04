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
typedef  int u8 ;
struct dst_state {int dummy; } ;

/* Variables and functions */
#define  DST_TYPE_IS_ATSC 131 
#define  DST_TYPE_IS_CABLE 130 
#define  DST_TYPE_IS_SAT 129 
#define  DST_TYPE_IS_TERR 128 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 

__attribute__((used)) static int dst_type_print(struct dst_state *state, u8 type)
{
	char *otype;
	switch (type) {
	case DST_TYPE_IS_SAT:
		otype = "satellite";
		break;

	case DST_TYPE_IS_TERR:
		otype = "terrestrial";
		break;

	case DST_TYPE_IS_CABLE:
		otype = "cable";
		break;

	case DST_TYPE_IS_ATSC:
		otype = "atsc";
		break;

	default:
		dprintk(2, "invalid dst type %d\n", type);
		return -EINVAL;
	}
	dprintk(2, "DST type: %s\n", otype);

	return 0;
}