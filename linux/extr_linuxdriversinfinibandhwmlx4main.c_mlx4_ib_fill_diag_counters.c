#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int flags2; } ;
struct TYPE_8__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT ; 
 TYPE_3__* diag_basic ; 
 TYPE_3__* diag_device_only ; 
 TYPE_3__* diag_ext ; 

__attribute__((used)) static void mlx4_ib_fill_diag_counters(struct mlx4_ib_dev *ibdev,
				       const char **name,
				       u32 *offset,
				       bool port)
{
	int i;
	int j;

	for (i = 0, j = 0; i < ARRAY_SIZE(diag_basic); i++, j++) {
		name[i] = diag_basic[i].name;
		offset[i] = diag_basic[i].offset;
	}

	if (ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_DIAG_PER_PORT) {
		for (i = 0; i < ARRAY_SIZE(diag_ext); i++, j++) {
			name[j] = diag_ext[i].name;
			offset[j] = diag_ext[i].offset;
		}
	}

	if (!port) {
		for (i = 0; i < ARRAY_SIZE(diag_device_only); i++, j++) {
			name[j] = diag_device_only[i].name;
			offset[j] = diag_device_only[i].offset;
		}
	}
}