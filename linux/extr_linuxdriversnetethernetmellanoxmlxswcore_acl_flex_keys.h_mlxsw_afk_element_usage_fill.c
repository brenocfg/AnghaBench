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
struct mlxsw_afk_element_usage {int dummy; } ;
typedef  enum mlxsw_afk_element { ____Placeholder_mlxsw_afk_element } mlxsw_afk_element ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afk_element_usage_add (struct mlxsw_afk_element_usage*,int const) ; 
 int /*<<< orphan*/  mlxsw_afk_element_usage_zero (struct mlxsw_afk_element_usage*) ; 

__attribute__((used)) static inline void
mlxsw_afk_element_usage_fill(struct mlxsw_afk_element_usage *elusage,
			     const enum mlxsw_afk_element *elements,
			     unsigned int elements_count)
{
	int i;

	mlxsw_afk_element_usage_zero(elusage);
	for (i = 0; i < elements_count; i++)
		mlxsw_afk_element_usage_add(elusage, elements[i]);
}