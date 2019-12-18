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
struct mtd_partitions {int nr_parts; int /*<<< orphan*/  parts; } ;
struct mtd_part_parser_data {int dummy; } ;
struct mtd_part_parser {char const* name; } ;
struct mtd_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int add_mtd_partitions (struct mtd_info*,int /*<<< orphan*/ ,int) ; 
 char** default_mtd_part_types ; 
 char** default_subpartition_types ; 
 scalar_t__ mtd_is_partition (struct mtd_info*) ; 
 int mtd_part_do_parse (struct mtd_part_parser*,struct mtd_info*,struct mtd_partitions*,struct mtd_part_parser_data*) ; 
 int mtd_part_of_parse (struct mtd_info*,struct mtd_partitions*) ; 
 int /*<<< orphan*/  mtd_part_parser_cleanup (struct mtd_partitions*) ; 
 struct mtd_part_parser* mtd_part_parser_get (char const* const) ; 
 int /*<<< orphan*/  mtd_part_parser_put (struct mtd_part_parser*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  request_module (char*,char const* const) ; 
 int /*<<< orphan*/  strcmp (char const* const,char*) ; 

int parse_mtd_partitions(struct mtd_info *master, const char *const *types,
			 struct mtd_part_parser_data *data)
{
	struct mtd_partitions pparts = { };
	struct mtd_part_parser *parser;
	int ret, err = 0;

	if (!types)
		types = mtd_is_partition(master) ? default_subpartition_types :
			default_mtd_part_types;

	for ( ; *types; types++) {
		/*
		 * ofpart is a special type that means OF partitioning info
		 * should be used. It requires a bit different logic so it is
		 * handled in a separated function.
		 */
		if (!strcmp(*types, "ofpart")) {
			ret = mtd_part_of_parse(master, &pparts);
		} else {
			pr_debug("%s: parsing partitions %s\n", master->name,
				 *types);
			parser = mtd_part_parser_get(*types);
			if (!parser && !request_module("%s", *types))
				parser = mtd_part_parser_get(*types);
			pr_debug("%s: got parser %s\n", master->name,
				parser ? parser->name : NULL);
			if (!parser)
				continue;
			ret = mtd_part_do_parse(parser, master, &pparts, data);
			if (ret <= 0)
				mtd_part_parser_put(parser);
		}
		/* Found partitions! */
		if (ret > 0) {
			err = add_mtd_partitions(master, pparts.parts,
						 pparts.nr_parts);
			mtd_part_parser_cleanup(&pparts);
			return err ? err : pparts.nr_parts;
		}
		/*
		 * Stash the first error we see; only report it if no parser
		 * succeeds
		 */
		if (ret < 0 && !err)
			err = ret;
	}
	return err;
}