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
struct mtd_partitions {int nr_parts; struct mtd_part_parser* parser; int /*<<< orphan*/  parts; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_part_parser {int (* parse_fn ) (struct mtd_info*,int /*<<< orphan*/ *,struct mtd_part_parser_data*) ;int /*<<< orphan*/  name; } ;
struct mtd_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ *,struct mtd_part_parser_data*) ; 

__attribute__((used)) static int mtd_part_do_parse(struct mtd_part_parser *parser,
			     struct mtd_info *master,
			     struct mtd_partitions *pparts,
			     struct mtd_part_parser_data *data)
{
	int ret;

	ret = (*parser->parse_fn)(master, &pparts->parts, data);
	pr_debug("%s: parser %s: %i\n", master->name, parser->name, ret);
	if (ret <= 0)
		return ret;

	pr_notice("%d %s partitions found on MTD device %s\n", ret,
		  parser->name, master->name);

	pparts->nr_parts = ret;
	pparts->parser = parser;

	return ret;
}