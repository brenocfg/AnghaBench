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
typedef  scalar_t__ u32 ;
struct unicam_device {int /*<<< orphan*/  cfg; TYPE_1__* fmt; } ;
struct TYPE_2__ {int depth; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNICAM_DEBL_MASK ; 
 int /*<<< orphan*/  UNICAM_IPIPE ; 
 int /*<<< orphan*/  UNICAM_PPM_MASK ; 
 int UNICAM_PPM_NONE ; 
 int UNICAM_PPM_PACK10 ; 
 int UNICAM_PPM_PACK12 ; 
 int UNICAM_PPM_PACK14 ; 
 int UNICAM_PPM_PACK16 ; 
 int UNICAM_PPM_PACK8 ; 
 int /*<<< orphan*/  UNICAM_PUM_MASK ; 
 int UNICAM_PUM_NONE ; 
 int UNICAM_PUM_UNPACK10 ; 
 int UNICAM_PUM_UNPACK12 ; 
 int UNICAM_PUM_UNPACK14 ; 
 int UNICAM_PUM_UNPACK16 ; 
 int UNICAM_PUM_UNPACK8 ; 
 int find_mbus_depth_by_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_field (scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unicam_set_packing_config(struct unicam_device *dev)
{
	int mbus_depth = find_mbus_depth_by_code(dev->fmt->code);
	int v4l2_depth = dev->fmt->depth;
	int pack, unpack;
	u32 val;

	if (mbus_depth == v4l2_depth) {
		unpack = UNICAM_PUM_NONE;
		pack = UNICAM_PPM_NONE;
	} else {
		switch (mbus_depth) {
		case 8:
			unpack = UNICAM_PUM_UNPACK8;
			break;
		case 10:
			unpack = UNICAM_PUM_UNPACK10;
			break;
		case 12:
			unpack = UNICAM_PUM_UNPACK12;
			break;
		case 14:
			unpack = UNICAM_PUM_UNPACK14;
			break;
		case 16:
			unpack = UNICAM_PUM_UNPACK16;
			break;
		default:
			unpack = UNICAM_PUM_NONE;
			break;
		}
		switch (v4l2_depth) {
		case 8:
			pack = UNICAM_PPM_PACK8;
			break;
		case 10:
			pack = UNICAM_PPM_PACK10;
			break;
		case 12:
			pack = UNICAM_PPM_PACK12;
			break;
		case 14:
			pack = UNICAM_PPM_PACK14;
			break;
		case 16:
			pack = UNICAM_PPM_PACK16;
			break;
		default:
			pack = UNICAM_PPM_NONE;
			break;
		}
	}

	val = 0;
	set_field(&val, 2, UNICAM_DEBL_MASK);
	set_field(&val, unpack, UNICAM_PUM_MASK);
	set_field(&val, pack, UNICAM_PPM_MASK);
	reg_write(&dev->cfg, UNICAM_IPIPE, val);
}