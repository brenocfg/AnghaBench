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

/* Variables and functions */
 char* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_FLD_SZ_BYTES (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  outer_headers ; 

__attribute__((used)) static bool outer_header_zero(u32 *match_criteria)
{
	int size = MLX5_FLD_SZ_BYTES(fte_match_param, outer_headers);
	char *outer_headers_c = MLX5_ADDR_OF(fte_match_param, match_criteria,
					     outer_headers);

	return outer_headers_c[0] == 0 && !memcmp(outer_headers_c,
						  outer_headers_c + 1,
						  size - 1);
}